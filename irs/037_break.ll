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
  store i32 0, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 0, i32* %v12
  %v17 = load i32, i32* %v9
  %bool_19 = icmp slt i32 %v17, 100
  %bool_21 = icmp ne i1 %bool_19, false
  br i1 %bool_21, label %while_entry15, label %next_entry16
while_entry15:
  %v25 = load i32, i32* %v9
  %bool_27 = icmp eq i32 %v25, 50
  br i1 %bool_27, label %if_true_entry22, label %next_entry24
next_entry16:
  %v34 = load i32, i32* %v12
  ret i32 %v34
if_true_entry22:
  br label %next_entry16
next_entry24:
  %v28 = load i32, i32* %v12
  %v29 = load i32, i32* %v9
  %v30 = add nsw i32 %v28, %v29
  store i32 %v30, i32* %v12
  %v31 = load i32, i32* %v9
  %v33 = add nsw i32 %v31, 1
  store i32 %v33, i32* %v9
  br i1 %bool_21, label %while_entry15, label %next_entry16
}

