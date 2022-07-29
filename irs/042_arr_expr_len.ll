@N11 = constant i32 -1
@arr27 = global [6 x i32] [ i32 1, i32 2, i32 33, i32 4, i32 5, i32 6 ]
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
main28:
  %v29 = alloca i32
  store i32 0, i32* %v29
  %v31 = alloca i32
  store i32 0, i32* %v31
  %v35 = load i32, i32* %v29
  %bool_37 = icmp slt i32 %v35, 6
  %bool_39 = icmp ne i1 %bool_37, false
  br i1 %bool_39, label %while_entry33, label %next_entry34
while_entry33:
  %v40 = load i32, i32* %v31
  %v41 = load i32, i32* %v29
  %v42 = getelementptr [6 x i32], [6 x i32]* @arr27, i32 0, i32 %v41
  %v43 = load i32, i32* %v42
  %v44 = add nsw i32 %v40, %v43
  store i32 %v44, i32* %v31
  %v45 = load i32, i32* %v29
  %v47 = add nsw i32 %v45, 1
  store i32 %v47, i32* %v29
  br i1 %bool_39, label %while_entry33, label %next_entry34
next_entry34:
  %v48 = load i32, i32* %v31
  ret i32 %v48
}

