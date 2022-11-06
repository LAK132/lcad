if get_option('lcad_enable_tests')
	lcadtest = static_library(
		'lcadtest',
		[
			'lcad.cpp',
		],
		override_options: 'cpp_std=' + version,
		dependencies: [
			lcad_dep,
		],
	)
else
	lcadtest = []
endif

lcadtest_dep = declare_dependency(
	link_whole: lcadtest,
)
