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
define i32 @ifElse() {
ifElse8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 5, i32* %v9
  %v15 = load i32, i32* %v9
  %bool_17 = icmp eq i32 %v15, 5
  br i1 %bool_17, label %if_true_entry12, label %if_false_entry13
if_true_entry12:
  store i32 25, i32* %v9
  br label %next_entry14
if_false_entry13:
  %v19 = load i32, i32* %v9
  %v21 = mul i32 %v19, 2
  store i32 %v21, i32* %v9
  br label %next_entry14
next_entry14:
  %v22 = load i32, i32* %v9
  ret i32 %v22
}
define i32 @main() {
main23:
  %v24 = call i32 @ifElse()
  ret i32 %v24
}

