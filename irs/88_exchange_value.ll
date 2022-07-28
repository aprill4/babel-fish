@n9 = global i32 zeroinitializer
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
main10:
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = call i32 @getint()
  store i32 %v15, i32* %v11
  %v16 = call i32 @getint()
  store i32 %v16, i32* %v13
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = load i32, i32* %v11
  store i32 %v19, i32* %v17
  %v20 = load i32, i32* %v13
  store i32 %v20, i32* %v11
  %v21 = load i32, i32* %v17
  store i32 %v21, i32* %v13
  %v22 = load i32, i32* %v11
  call void @putint(i32 %v22)
  store i32 10, i32* %v17
  %v25 = load i32, i32* %v17
  call void @putch(i32 %v25)
  %v27 = load i32, i32* %v13
  call void @putint(i32 %v27)
  store i32 10, i32* %v17
  %v30 = load i32, i32* %v17
  call void @putch(i32 %v30)
  ret i32 0
}

