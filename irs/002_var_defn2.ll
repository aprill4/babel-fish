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
  %v15 = alloca i32
  store i32 5, i32* %v15
  %v17 = load i32, i32* %v15
  %v18 = load i32, i32* @b13
  %v19 = add nsw i32 %v17, %v18
  ret i32 %v19
}

