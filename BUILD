load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")


cc_library(
    name = "file_stream",
    srcs = ["file_stream.cc"],
    hdrs = ["file_stream.h", "stream_interface.h"],
    deps = [
  			"@abseil-cpp//absl/status:status",
  			"@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
				#"@abseil-cpp//absl/container:flat_hash_map",
    ],
)

cc_library(
	  name = "token",
		srcs = ["token.cc"],
		hdrs = ["token.h"],
		deps = [
  			"@abseil-cpp//absl/status:status",
  			"@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
		],
);

cc_library(
    name = "lexer",
    srcs = ["lexer.cc"],
    hdrs = ["lexer.h"],
    deps = [
			  ":file_stream",
				":token",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/container:flat_hash_map",
    ],
)

cc_binary(
    name = "basic36",
    srcs = ["main.cc"],
    deps = [
			  ":file_stream",
        ":lexer",
				":token",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
)

cc_test(
    name = "lexer_tests",
    size = "small",
    srcs = ["lexer_tests.cc"],
    deps = [
        ":lexer",
        "@googletest//:gtest_main", 
    ],
)

cc_test(
    name = "file_stream_tests",
    size = "small",
    srcs = ["file_stream_tests.cc"],
		data = [
			"test_data/empty.txt",
			"test_data/line_column.txt",
		],
    deps = [
        ":file_stream",
  			"@abseil-cpp//absl/status:status",
  			"@abseil-cpp//absl/status:status_matchers",
  			"@abseil-cpp//absl/status:statusor",
        "@abseil-cpp//absl/strings",
        "@googletest//:gtest_main", 
    ],
)
