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
define i32 @get_one(i32 ) {
get_one9:
  %v10 = alloca i32
  ret i32 1
}
define i32 @deepWhileBr(i32 , i32 ) {
deepWhileBr14:
  %v15 = alloca i32
  %v16 = alloca i32
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = load i32, i32* %v15
  %v20 = load i32, i32* %v16
  %v21 = add nsw i32 %v19, %v20
  store i32 %v21, i32* %v17
  %v24 = load i32, i32* %v17
  %bool_26 = icmp slt i32 %v24, 75
  %bool_28 = icmp ne i1 %bool_26, false
  br i1 %bool_28, label %while_entry22, label %next_entry23
while_entry22:
  %v29 = alloca i32
  store i32 zeroinitializer, i32* %v29
  store i32 42, i32* %v29
  %v35 = load i32, i32* %v17
  %bool_37 = icmp slt i32 %v35, 100
  br i1 %bool_37, label %if_true_entry32, label %next_entry34
next_entry23:
  %v62 = load i32, i32* %v17
  ret i32 %v62
if_true_entry32:
  %v38 = load i32, i32* %v17
  %v39 = load i32, i32* %v29
  %v40 = add nsw i32 %v38, %v39
  store i32 %v40, i32* %v17
  %v44 = load i32, i32* %v17
  %bool_46 = icmp sgt i32 %v44, 99
  br i1 %bool_46, label %if_true_entry41, label %next_entry43
next_entry34:
  br i1 %bool_28, label %while_entry22, label %next_entry23
if_true_entry41:
  %v47 = alloca i32
  store i32 zeroinitializer, i32* %v47
  %v49 = load i32, i32* %v29
  %v51 = mul i32 %v49, 2
  store i32 %v51, i32* %v47
  %v56 = call i32 @get_one(i32 0)
  %bool_58 = icmp eq i32 %v56, 1
  br i1 %bool_58, label %if_true_entry52, label %next_entry54
next_entry43:
  br label %next_entry34
if_true_entry52:
  %v59 = load i32, i32* %v47
  %v61 = mul i32 %v59, 2
  store i32 %v61, i32* %v17
  br label %next_entry54
next_entry54:
  br label %next_entry43
}
define i32 @main() {
main63:
  %v64 = alloca i32
  store i32 zeroinitializer, i32* %v64
  store i32 2, i32* %v64
  %v67 = load i32, i32* %v64
  %v68 = load i32, i32* %v64
  %v69 = call i32 @deepWhileBr(i32 %v67, i32 %v68)
  store i32 %v69, i32* %v64
  %v70 = load i32, i32* %v64
  call void @putint(i32 %v70)
  ret i32 0
}

