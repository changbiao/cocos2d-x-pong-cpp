#!/usr/bin/python

import sys
import os, os.path
import shutil
from optparse import OptionParser

def get_num_of_cpu():
  ''' The build process can be accelerated by running multiple concurrent jobs using the `-j` option.
  '''
  try:
    platform = sys.platform
    if platform == 'win32':
      if 'NUMBER_OF_PROCESSORS' in os.environ:
        return int(os.environ['NUMBER_OF_PROCESSORS'])
      else:
        return 1
    else:
      from numpy.distutils import cpuinfo
      return cpuinfo.cpu._getNCPUs()
  except Exception:
    print 'Using default 1 CPU.'
    return 1

def check_environment_variables_sdk():
  ''' Checking the environment variable `ANDROID_SDK_ROOT`.
  '''

  try:
    SDK_ROOT = os.environ['ANDROID_SDK_ROOT']
  except Exception:
    print 'ANDROID_SDK_ROOT not defined.'
    sys.exit(1)

  return SDK_ROOT

def check_environment_variables():
  ''' Checking the environment variable `NDK_ROOT`.
  '''

  try:
    NDK_ROOT = os.environ['NDK_ROOT']
  except Exception:
    print 'NDK_ROOT not defined.'
    sys.exit(1)

  return NDK_ROOT

def select_toolchain_version():
  ''' Different NDKs use different GCC versions:
  ndk-r8e -> gcc4.7
  ndk-r9  -> gcc4.8
  '''

  ndk_root = check_environment_variables()
  if os.path.isdir(os.path.join(ndk_root, 'toolchains/arm-linux-androideabi-4.8')):
    os.environ['NDK_TOOLCHAIN_VERSION'] = '4.8'
    print 'The selected NDK toolchain version was 4.8.'
  elif os.path.isdir(os.path.join(ndk_root, 'toolchains/arm-linux-androideabi-4.7')):
    os.environ['NDK_TOOLCHAIN_VERSION'] = '4.7'
    print 'The selected NDK toolchain version was 4.7.'
  else:
    print 'Could not find the GCC toolchain.'
    exit(1)

def do_build(cocos_root, ndk_root, app_android_root, ndk_build_param, sdk_root, android_platform, build_mode):

  ndk_path = os.path.join(ndk_root, 'ndk-build')

  platform = sys.platform
  if platform == 'win32':
    ndk_module_path = 'NDK_MODULE_PATH=%s;%s/external;%s/cocos' % (cocos_root, cocos_root, cocos_root)
  else:
    ndk_module_path = 'NDK_MODULE_PATH=%s:%s/external:%s/cocos' % (cocos_root, cocos_root, cocos_root)

  num_of_cpu = get_num_of_cpu()

  if ndk_build_param == None:
    command = '%s -j%d -C %s %s' % (ndk_path, num_of_cpu, app_android_root, ndk_module_path)
  else:
    command = '%s -j%d -C %s %s %s' % (ndk_path, num_of_cpu, app_android_root, ''.join(str(e) for e in ndk_build_param), ndk_module_path)
  if os.system(command) != 0:
    raise Exception('Build dynamic library for project [ ' + app_android_root + ' ] fails!')
  elif android_platform is not None:
    sdk_tool_path = os.path.join(sdk_root, 'tools/android')
    cocoslib_path = os.path.join(cocos_root, 'cocos/2d/platform/android/java')
    command = '%s update lib-project -t %s -p %s' % (sdk_tool_path, android_platform, cocoslib_path)
    if os.system(command) != 0:
      raise Exception('update cocos lib-project [ ' + cocoslib_path + ' ] fails!')
    command = '%s update project -t %s -p %s -s' % (sdk_tool_path, android_platform, app_android_root)
    if os.system(command) != 0:
      raise Exception('Update project [ ' + app_android_root + ' ] fails!')
    buildfile_path = os.path.join(app_android_root, 'build.xml')
    command = 'ant clean %s -f %s -Dsdk.dir=%s' % (build_mode, buildfile_path, sdk_root)
    os.system(command)

def copy_files(src, dst):

  for item in os.listdir(src):
    path = os.path.join(src, item)
    # Android can not package files that ends with `.gz`.
    if not item.startswith('.') and not item.endswith('.gz') and os.path.isfile(path):
      shutil.copy(path, dst)
    if os.path.isdir(path):
      new_dst = os.path.join(dst, item)
      os.mkdir(new_dst)
      copy_files(path, new_dst)

def copy_resources(app_android_root):

  # Remove app_android_root/assets if it exists.
  assets_dir = os.path.join(app_android_root, 'assets')
  if os.path.isdir(assets_dir):
      shutil.rmtree(assets_dir)

  # Copy resources.
  os.mkdir(assets_dir)
  resources_dir = os.path.join(app_android_root, '../Resources')
  if os.path.isdir(resources_dir):
    copy_files(resources_dir, assets_dir)

def build(ndk_build_param,android_platform,build_mode):

  ndk_root = check_environment_variables()
  sdk_root = None
  select_toolchain_version()

  current_dir = os.path.dirname(os.path.realpath(__file__))
  cocos_root = os.path.join(current_dir, '../cocos2d')

  app_android_root = current_dir
  copy_resources(app_android_root)

  if android_platform is not None:
    sdk_root = check_environment_variables_sdk()
    if android_platform.isdigit():
      android_platform = 'android-' + android_platform
    else:
      print 'Please use a vaild android platform.'
      exit(1)

  if build_mode is None:
    build_mode = 'debug'
  elif build_mode != 'release':
    build_mode = 'debug'

  do_build(cocos_root, ndk_root, app_android_root, ndk_build_param, sdk_root, android_platform, build_mode)


if __name__ == '__main__':

  parser = OptionParser()
  parser.add_option('-n', '--ndk', dest='ndk_build_param',
      help='Parameter for ndk-build.')
  parser.add_option('-p', '--platform', dest='android_platform',
    help='Parameter for android-update.')
  parser.add_option('-b', '--build', dest='build_mode',
    help='Build mode for java project (http://developer.android.com/tools/building/building-cmdline.html).')
  (opts, args) = parser.parse_args()

  build(opts.ndk_build_param, opts.android_platform, opts.build_mode)
