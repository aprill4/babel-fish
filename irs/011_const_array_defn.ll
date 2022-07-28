@a15 = constant [5 x i32] [ i32 0, i32 1, i32 2, i32 3, i32 4 ]
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
main16:
  %v19 = getelementptr [5 x i32], [5 x i32]* @a15, i32 0, i32 4
  %v20 = load i32, i32* %v19
  ret i32 %v20
}

