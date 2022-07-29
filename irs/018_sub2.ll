@a10 = constant i32 10
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
main11:
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 2, i32* %v12
  %v15 = load i32, i32* %v12
  %v16 = sub nsw i32 %v15, 10
  ret i32 %v16
}

