cc_test(
    name = "binary_tree_test",
    srcs = ["binary_tree_test.cc"],
    deps = [
        "//src:binary_tree",
        "@com_google_googletest//:gtest_main",
    ],
    copts = ["-fprofile-arcs", "-ftest-coverage"],
    linkopts = ["-lgcov"],
) 