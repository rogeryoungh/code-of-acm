add_rules("mode.debug", "mode.release")

set_optimize("faster") -- O2
add_cxxflags("-Wall", "-Wextra", "-Wshadow")

target("src")
    set_kind("object")
    add_includedirs("src/", {public = true})
    add_includedirs("picobench/include", {public = true})

target("ntt-newton")
    set_kind("binary")
    add_deps("src")
    add_files("src/poly/ntt-newton-test.cpp")
    on_run(function (target)
        os.run("./build/linux/x86_64/release/ntt-newton --output=build/poly-ntt-newton.info")
    end)

target("ntt-newton-fast")
    set_kind("binary")
    add_deps("src")
    add_files("src/poly/ntt-newton-fast-test.cpp")
    on_run(function (target)
        os.run("./build/linux/x86_64/release/ntt-newton-fast --output=build/poly-ntt-newton-fast.info")
    end)
