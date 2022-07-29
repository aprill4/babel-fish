@a10 = global i32 7
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
define i32 @func() {
func11:
  %v12 = alloca i32
  %v13 = load i32, i32* @a10
  store i32 %v13, i32* %v12
  %v14 = alloca i32
  store i32 1, i32* %v14
  %v19 = load i32, i32* %v14
  %v20 = load i32, i32* %v12
  %bool_21 = icmp eq i32 %v19, %v20
  br i1 %bool_21, label %if_true_entry16, label %if_false_entry17
if_true_entry16:
  %v22 = load i32, i32* %v14
  %v24 = add nsw i32 %v22, 1
  store i32 %v24, i32* %v14
  ret i32 1
if_false_entry17:
  ret i32 0
next_entry18:
  ret i32 zeroinitializer
}
define i32 @main() {
main28:
  %v29 = alloca i32
  store i32 0, i32* %v29
  %v31 = alloca i32
  store i32 0, i32* %v31
  %v35 = load i32, i32* %v31
  %bool_37 = icmp slt i32 %v35, 100
  %bool_39 = icmp ne i1 %bool_37, false
  br i1 %bool_39, label %while_entry33, label %next_entry34
while_entry33:
  %v43 = call i32 @func()
  %bool_45 = icmp eq i32 %v43, 1
  br i1 %bool_45, label %if_true_entry40, label %next_entry42
next_entry34:
  %v55 = load i32, i32* %v29
  %bool_57 = icmp slt i32 %v55, 100
  br i1 %bool_57, label %if_true_entry52, label %if_false_entry53
if_true_entry40:
  %v46 = load i32, i32* %v29
  %v48 = add nsw i32 %v46, 1
  store i32 %v48, i32* %v29
  br label %next_entry42
next_entry42:
  %v49 = load i32, i32* %v31
  %v51 = add nsw i32 %v49, 1
  store i32 %v51, i32* %v31
  br i1 %bool_39, label %while_entry33, label %next_entry34
if_true_entry52:
  call void @putint(i32 1)
  br label %next_entry54
if_false_entry53:
  call void @putint(i32 0)
  br label %next_entry54
next_entry54:
  ret i32 0
}

