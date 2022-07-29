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
define i32 @defn() {
defn8:
  ret i32 4
}
define i32 @main() {
main10:
  %v11 = alloca i32
  %v12 = call i32 @defn()
  store i32 %v12, i32* %v11
  %v13 = load i32, i32* %v11
  ret i32 %v13
}

