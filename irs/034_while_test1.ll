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
define i32 @doubleWhile() {
doubleWhile8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 5, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 7, i32* %v12
  %v17 = load i32, i32* %v9
  %bool_19 = icmp slt i32 %v17, 100
  %bool_21 = icmp ne i1 %bool_19, false
  br i1 %bool_21, label %while_entry15, label %next_entry16
while_entry15:
  %v22 = load i32, i32* %v9
  %v24 = add nsw i32 %v22, 30
  store i32 %v24, i32* %v9
  %v27 = load i32, i32* %v12
  %bool_29 = icmp slt i32 %v27, 100
  %bool_31 = icmp ne i1 %bool_29, false
  br i1 %bool_31, label %while_entry25, label %next_entry26
next_entry16:
  %v38 = load i32, i32* %v12
  ret i32 %v38
while_entry25:
  %v32 = load i32, i32* %v12
  %v34 = add nsw i32 %v32, 6
  store i32 %v34, i32* %v12
  br i1 %bool_31, label %while_entry25, label %next_entry26
next_entry26:
  %v35 = load i32, i32* %v12
  %v37 = sub nsw i32 %v35, 100
  store i32 %v37, i32* %v12
  br i1 %bool_21, label %while_entry15, label %next_entry16
}
define i32 @main() {
main39:
  %v40 = call i32 @doubleWhile()
  ret i32 %v40
}

