@a10 = constant i32 10
@b13 = constant i32 5
define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @main() {
main14:
  %v15 = load i32, i32* @b13
  ret i32 %v15
}

