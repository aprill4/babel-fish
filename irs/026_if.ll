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
define i32 @main() {
main10:
  store i32 10, i32* @a9
  %v15 = load i32, i32* @a9
  %bool_17 = icmp sgt i32 %v15, 0
  br i1 %bool_17, label %if_true_entry12, label %next_entry14
if_true_entry12:
  ret i32 1
next_entry14:
  ret i32 0
}

