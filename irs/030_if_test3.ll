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
define i32 @ififElse() {
ififElse8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 5, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 10, i32* %v12
  %v18 = load i32, i32* %v9
  %bool_20 = icmp eq i32 %v18, 5
  br i1 %bool_20, label %if_true_entry15, label %next_entry17
if_true_entry15:
  %v24 = load i32, i32* %v12
  %bool_26 = icmp eq i32 %v24, 10
  br i1 %bool_26, label %if_true_entry21, label %if_false_entry22
next_entry17:
  %v31 = load i32, i32* %v9
  ret i32 %v31
if_true_entry21:
  store i32 25, i32* %v9
  br label %next_entry23
if_false_entry22:
  %v28 = load i32, i32* %v9
  %v30 = add nsw i32 %v28, 15
  store i32 %v30, i32* %v9
  br label %next_entry23
next_entry23:
  br label %next_entry17
}
define i32 @main() {
main32:
  %v33 = call i32 @ififElse()
  ret i32 %v33
}

