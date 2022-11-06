git_tag_header = vcs_tag(
  command: ['git', 'describe', '--tags', '--always', '--abbrev=0'],
  fallback: 'v0.0.0',
  input: 'git_tag.txt',
  output: 'git_tag.hpp',
  replace_string: '@GIT_TAG@',
)

git_hash_header = vcs_tag(
  command: ['git', 'rev-parse', '--short', 'HEAD'],
  fallback: '0000000',
  input: 'git_hash.txt',
  output: 'git_hash.hpp',
  replace_string: '@GIT_HASH@',
)

git_header = [git_tag_header, git_hash_header]

lak_dep = subproject('lak').get_variable('lak_dep')
libfive_dep = subproject('libfive').get_variable('libfive_dep')

lcad_includes = include_directories('../include')

lcad_dependencies = declare_dependency(
	dependencies: [
		lak_dep,
		libfive_dep,
	],
)

lcad = static_library(
	'liblcad',
	[
		'lcad.cpp',
	],
	override_options: 'cpp_std=' + version,
	include_directories: lcad_includes,
	dependencies: lcad_dependencies,
)

lcad_dep = declare_dependency(
	link_with: lcad,
	include_directories: lcad_includes,
	dependencies:
		lcad_dependencies.partial_dependency(includes:true, compile_args: true),
)

lcadmain = static_library(
	'lcadmain',
	[
		'main.cpp',
	],
	override_options: 'cpp_std=' + version,
	include_directories: lcad_includes,
	dependencies: [
		lcad_dep,
	],
)
