typedef void (*sighandler_t)(int); /* type definition for return handler */
static jmp_buf jbuf;            /* setup as global/static for sigsetjmp and siglongjmp */

/* signal handler */
void handler(int signo)
{
    /* issue siglongjmp */
    siglongjmp(jbuf, 1);
}


int safeWrite(int* ptr, int val)
{
    int status = 0;
    int set_jump;

    /* call signal and keep old handler */
    signal(SIGSEGV, handler);

    /* check if ptr is NULL and set sigsetjmp to be able to return */
    /* try to write the value at the specified memory location */
    set_jump = sigsetjmp(jbuf, 1);
    if(set_jump == 0) {
        // the first time we set the sigsetjmp to restore in case of seg fault the value is 0
        *ptr = val;    
    }
    else {
        //this means that a seg fault has been thrown which means we have to set status to 1
        status = 1;
    }

    /* handle success/error */

    /* revert to old handler */
    signal(SIGSEGV, SIG_IGN);

    return status;

}
