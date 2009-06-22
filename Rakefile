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


namespace :profile do
  # OFX_PATH="apps/moreExamples/memoMSAFluidExample" /usr/local/ruby186/bin/rake profile:pprof
  # OFX_PATH=apps/moreExamples/* rake profile:pprof
  desc 'cpu_profile via pprof (google-preftools) requires ENV["OFX_PATH"]'
  task :pprof do
    return puts('pprof not installed.') unless system 'which pprof'
    return puts('no ENV["OFX_PATH"] given') unless ENV['OFX_PATH']

    out_dir = ENV['PPROF_OUT'] || Dir.pwd+"/other/pprof-results"
    FileUtils.mkdir_p(out_dir) unless File.exists? out_dir
    dirs = Dir[ "#{ENV['OFX_PATH']}/bin/*.app" ].reverse

    #_dirs = dirs.is_a?(String) ? [ dirs ] : dirs
    dirs.collect { |path|
      odir = Dir.pwd;
      begin
        Dir.chdir File.dirname(File.dirname(path))

        proj = { :name => File.basename(Dir.pwd)  }
        proj[:profile_name] = "pprof-#{proj[:name]}_#{Time.now.to_i.to_s[3..-1]}"

        bin_path = "bin/"+File.basename(File.basename(path))+"/Contents/MacOS/#{File.basename(path).gsub(".app",'')}"
        if File.read(bin_path).match("profiler")

          prof_cmd = "env CPUPROFILE_FREQUENCY=#{ENV['CPUPROFILE_FREQUENCY'] || 50} CPUPROFILE=#{out_dir}#{proj[:profile_name]}.prof ./#{bin_path}"
          # prof_gif = "pprof --pdf ../#{proj[:name]}/#{bin_path} #{out_dir}#{proj[:profile_name]}.prof > #{out_dir}#{proj[:profile_name]}.pdf"
          prof_gif = "pprof --gif ../#{proj[:name]}/#{bin_path} #{out_dir}#{proj[:profile_name]}.prof > #{out_dir}#{proj[:profile_name]}.gif"
          cmds = [Dir.pwd, prof_cmd, prof_gif, "open #{out_dir}#{proj[:profile_name]}.gif"]


          msg = "pprof #{proj[:name]}/bin/#{File.basename bin_path}"
          puts "INVOKE: " + msg
          unless ENV['DEBUG']
            cmds[1..-1].collect { |cmd| system cmd }
          else
            print cmds.to_yaml
          end
          puts "\nFINISHED: " + msg
        else
          puts("\nWARNING: #{proj[:name]}/bin/#{File.basename bin_path} is not linked to -lprofiler, needs to recompile first!")
        end
      rescue Exception => e
        puts [e.inspect, e.backtrace]
        Dir.chdir(odir); puts Dir.pwd
      ensure
        Dir.chdir(odir)
      end
    }
  end

end
