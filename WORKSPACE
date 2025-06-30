workspace(name = "binary_tree")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Google Test
http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz"],
    strip_prefix = "googletest-1.14.0",
)

# Gcovr for coverage reports
http_archive(
    name = "gcovr",
    urls = ["https://github.com/gcovr/gcovr/archive/refs/tags/5.2.tar.gz"],
    strip_prefix = "gcovr-5.2",
    build_file = "//third_party:gcovr.BUILD",
) 