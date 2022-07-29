@a10 = global i32 3
@b13 = global i32 5
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
  %v15 = load i32, i32* @a10
  %v16 = load i32, i32* @b13
  %v17 = add nsw i32 %v15, %v16
  ret i32 %v17
}

