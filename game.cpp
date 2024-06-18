class Game


void enableRawMode() {

  // gets current parameter for terminals
  // with error handling
  //
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) {
    die("tcsetattr");
  }

  // When leaving this program exit raw mode
  //
  atexit(disableRawMode);

  // create a copy of the current struct to manipulate
  //
  struct termios raw = E.orig_termios;

  // Set flags
  // ECHO = let characters show as you type them
  // ICANON = Canonical mode
  // ISIG = Ctrl-C and Ctrl-Z
  // XIXON = Ctrl-S and Ctrl -Q
  // IEXTEN = Ctrl-V
  // ICRNL = Ctrl-M
  // OPOST = Output processing
  // CS8 = bitsize
  // BRKINT = Break condition to end program
  // ISTRIP = Bit stripping 8th bit -> 0
  // INPCK = Parity checking
  //
  raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  // VMIN sets minimum number of bits to be read
  // VTIME sets maximum amount of time to wait before
  // read()
  //
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  // sets parameters to what we declared above
  // with error handling
  //
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    die("tcsetattr");
  }
}

