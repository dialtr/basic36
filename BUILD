load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

# 1. The Core Library
cc_library(
    name = "lexer",
    srcs = ["lexer.cc"],
    hdrs = ["lexer.h"], # Assuming you have a header for the implementation
    deps = [
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/container:flat_hash_map",
    ],
)

# 2. The Main Binary
cc_binary(
    name = "basic36",
    srcs = ["main.cc"],
    deps = [
        ":lexer",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
)

# 3. The Unit Test
cc_test(
    name = "lexer_test",
    size = "small",
    srcs = ["lexer_tests.cc"],
    deps = [
        ":lexer",
        "@googletest//:gtest_main", 
    ],
)
