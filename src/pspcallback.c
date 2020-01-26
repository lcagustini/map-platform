int PSPExitCallback(int arg1, int arg2, void *common) {
	sceKernelExitGame();

	return 0;
}

int PSPCallbackThread(SceSize args, void *argp) {
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", PSPExitCallback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

int PSPSetupCallbacks(void) {
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", PSPCallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
