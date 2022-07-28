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
define i32 @ifWhile() {
ifWhile8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 0, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 3, i32* %v12
  %v18 = load i32, i32* %v9
  %bool_20 = icmp eq i32 %v18, 5
  br i1 %bool_20, label %if_true_entry15, label %if_false_entry16
if_true_entry15:
  %v23 = load i32, i32* %v12
  %bool_25 = icmp eq i32 %v23, 2
  %bool_27 = icmp ne i1 %bool_25, false
  br i1 %bool_27, label %while_entry21, label %next_entry22
if_false_entry16:
  %v36 = load i32, i32* %v9
  %bool_38 = icmp slt i32 %v36, 5
  %bool_40 = icmp ne i1 %bool_38, false
  br i1 %bool_40, label %while_entry34, label %next_entry35
next_entry17:
  %v47 = load i32, i32* %v12
  ret i32 %v47
while_entry21:
  %v28 = load i32, i32* %v12
  %v30 = add nsw i32 %v28, 2
  store i32 %v30, i32* %v12
  br i1 %bool_27, label %while_entry21, label %next_entry22
next_entry22:
  %v31 = load i32, i32* %v12
  %v33 = add nsw i32 %v31, 25
  store i32 %v33, i32* %v12
  br label %next_entry17
while_entry34:
  %v41 = load i32, i32* %v12
  %v43 = mul i32 %v41, 2
  store i32 %v43, i32* %v12
  %v44 = load i32, i32* %v9
  %v46 = add nsw i32 %v44, 1
  store i32 %v46, i32* %v9
  br i1 %bool_40, label %while_entry34, label %next_entry35
next_entry35:
  br label %next_entry17
}
define i32 @main() {
main48:
  %v49 = call i32 @ifWhile()
  ret i32 %v49
}

