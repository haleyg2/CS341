
int main(int argc,char **argv)

{
  int iVar1;
  __sighandler_t p_Var2;
  char **argv_local;
  int argc_local;
  char c;

  iVar1 = getopt(argc,argv,"h");
  if ((char)iVar1 == -1) {
    p_Var2 = __sysv_signal(0xe,sigalrm_handler);
    if (p_Var2 == (__sighandler_t)0xffffffffffffffff) {
      fwrite("Unable to install SIGALRM handler\n",1,0x22,stderr);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    alarm(0x14);
    test_csim();
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  if ((char)iVar1 == 'h') {
    usage(argv);
                    /* WARNING: Subroutine does not return */
    exit(0);
  }
  usage(argv);
                    /* WARNING: Subroutine does not return */
  exit(1);
