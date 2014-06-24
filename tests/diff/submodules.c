#include "diff_helpers.h"
	cl_git_sandbox_cleanup();
#define get_buf_ptr(buf) ((buf)->asize ? (buf)->ptr : NULL)

	git_buf buf = GIT_BUF_INIT;
		if (expected[d] && !strcmp(expected[d], "<UNTRACKED>")) {
			cl_assert_at_line(delta->status == GIT_DELTA_UNTRACKED, file, line);
			continue;
		}
			cl_git_pass(git_patch_to_buf(&buf, patch));
		cl_git_pass(git_patch_to_buf(&buf, patch));
			"%s", expected[d], get_buf_ptr(&buf));
		git_buf_free(&buf);
	static const char *expected_none[] = {
		"<END>"
	};
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"<UNTRACKED>", /* sm_changed_head- */
		"<UNTRACKED>", /* sm_changed_head_ */
	/* bracket existing submodule with similarly named items */
	cl_git_mkfile("submod2/sm_changed_head-", "hello");
	cl_git_mkfile("submod2/sm_changed_head_", "hello");

	git_submodule_free(sm);

	git_submodule_free(sm);

		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */
		"<UNTRACKED>", /* not-submodule */
		"<UNTRACKED>", /* not */

void test_diff_submodules__skips_empty_includes_used(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;

	/* A side effect of of Git's handling of untracked directories and
	 * auto-ignoring of ".git" entries is that a newly initialized Git
	 * repo inside another repo will be skipped by diff, but one that
	 * actually has a commit it in will show as an untracked directory.
	 * Let's make sure that works.
	 */

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(0, exp.files);
	git_diff_free(diff);

	{
		git_repository *r2;
		cl_git_pass(git_repository_init(&r2, "empty_standard_repo/subrepo", 0));
		git_repository_free(r2);
	}

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(1, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
	git_diff_free(diff);

	cl_git_mkfile("empty_standard_repo/subrepo/README.txt", "hello\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(1, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNTRACKED]);
	git_diff_free(diff);
}