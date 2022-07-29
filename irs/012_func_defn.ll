@a9 = global i32 zeroinitializer
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
define i32 @func(i32 ) {
func11:
  %v12 = alloca i32
  %v13 = load i32, i32* %v12
  %v15 = sub nsw i32 %v13, 1
  store i32 %v15, i32* %v12
  %v16 = load i32, i32* %v12
  ret i32 %v16
}
define i32 @main() {
main17:
  %v18 = alloca i32
  store i32 zeroinitializer, i32* %v18
  store i32 10, i32* @a9
  %v21 = load i32, i32* @a9
  %v22 = call i32 @func(i32 %v21)
  store i32 %v22, i32* %v18
  %v23 = load i32, i32* %v18
  ret i32 %v23
}

