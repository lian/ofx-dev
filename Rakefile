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