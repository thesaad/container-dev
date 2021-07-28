## SPADE Examples ##

This directory contains SPADE examples for system activity scenarios, and relevant logs.

## Adding an Example ##

The following describes how to add a new example.

Give the example an appropriate descriptive name and create a directory with that name in the `examples` directory.

Add a `README.md` detailing the example. The details of the example include the following (with the goal in mind that someone else should be able to reproduce the example):

* What was the activity performed? - Upload any steps, scripts or source files necessary for performing the activity in the `program` directory.
* Upload the corresponding SPADE log (gzipped)
* Upload the corresponding Linux Audit log (gzipped) - If the log exceeds 1MB then name it as `container-dev-audit-log-<example_name>-<commit_hash>.log.gz` and share it separately rather than uploading it to git. The `commit_hash` refers to the commit hash of `container-dev` repo for the corresponding example. NOTE: In SPADE, the Audit reporter can be given the additional argument `outputLog=<Path to audit log>` to save only the consumed audit log rather than using the system audit log.

If the behaviour (of the example) is unexpected i.e. missing edges, unidentified annotation values, and etc. then provide the additional extra information:

* Was there any audit event loss when the activity was performed? This can be checked using the command `auditctl -s`.
* What should have been in the SPADE graph or the issue in the SPADE graph?
* What SPADE queries were tried? - Upload the queries in the directory `query`.
* If there are any graphs related to the queries then upload them in the directory `graphs`. Avoid uploading large files, and use the same naming convention as for the audit log mentioned above.
