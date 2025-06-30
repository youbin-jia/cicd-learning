load("@rules_cc//cc:defs.bzl", "cc_test")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def coverage_test(name, srcs, deps, **kwargs):
    """Custom test rule that generates coverage reports."""
    cc_test(
        name = name,
        srcs = srcs,
        deps = deps,
        copts = ["-fprofile-arcs", "-ftest-coverage"],
        linkopts = ["-lgcov"],
        **kwargs
    ) 