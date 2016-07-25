config QUICKLAKE
	bool "Quicklake"
	help
		Quicklake can accelerate the initialization of programs.

config QUICKLAKE_OPT_O0
	bool "Close GCC optimization"
	depends on QUICKLAKE
	help
		Generate readable assembly code
