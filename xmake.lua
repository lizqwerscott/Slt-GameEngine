-- 定义项目名和版本
set_project("slt")
set_version("0.0.1")

-- 设置编译选项
set_languages("c++20")
add_rules("mode.debug", "mode.release")
add_cxxflags("-g", "-Wall")

package("box2d")
    set_urls("https://github.com/erincatto/box2d.git")
    add_deps("cmake")
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

add_requires("box2d")
add_requires("sfml", {system = true})

add_includedirs("include")

local src_files = os.files("src/**/*.cpp")

target("slt")
   set_kind("static")
   set_basename("slt")
   add_files(src_files)
   add_headerfiles("include/(**.h)")

   add_packages("box2d")
   add_packages("sfml")
   add_links("GL", "dl")
