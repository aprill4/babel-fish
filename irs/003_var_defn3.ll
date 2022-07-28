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
main8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  store i32 1, i32* %v9
  store i32 2, i32* %v11
  store i32 3, i32* %v13
  %v18 = load i32, i32* %v11
  %v19 = load i32, i32* %v13
  %v20 = add nsw i32 %v18, %v19
  ret i32 %v20
}

