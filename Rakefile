require 'rake'

namespace :build do
  desc 'build ALL examples'
  task :examples do
    # ... xcodebuild -configuration Release -target "openFrameworks" -project "openFrameworks.xcodeproj"
  end  
end

namespace :clean do
  desc 'clean ALL'
  task :all do # :all => [:vm, :shred, :runtime]
    dirs = %{apps/*xamples/**/openFrameworksDebug.app apps/*xamples/**/openFrameworks.app apps/*xamples/**/build}
    files = %{**/*.xcodeproj/*.pbxuser **/*.xcodeproj/*.mode*}
    # ..
  end
end

XCODE_TEMPLATE_DIRECTORY = '/Library/Application Support/Developer/Shared/Xcode/Project Templates'
GROUP_DIRECTORY_NAME = 'Application'
TEMPLATE_NAME = 'openFrameworks Application'
namespace :install do
  desc 'install Xcode openFrameworks project template'
  task :xcode_template do
    path = File.join(XCODE_TEMPLATE_DIRECTORY, GROUP_DIRECTORY_NAME)
    FileUtils.mkdir_p(path) unless File.exists? path
    path = File.join(path, TEMPLATE_NAME)
    # NB - perhaps should remove old version when present
    # FileUtils.rm_r(path) if File.exists? path
    FileUtils.cp_r('other/xcode_template', path)
  end
end
