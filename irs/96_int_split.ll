@N9 = global i32 zeroinitializer
@newline11 = global i32 zeroinitializer
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
define i32 @split(i32 , i32* ) {
split14:
  %v15 = alloca i32
  %v16 = alloca i32
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = load i32, i32* @N9
  %v21 = sub nsw i32 %v19, 1
  store i32 %v21, i32* %v17
  %v24 = load i32, i32* %v17
  %v27 = sub nsw i32 0, 1
  %bool_28 = icmp ne i32 %v24, %v27
  %bool_30 = icmp ne i1 %bool_28, false
  br i1 %bool_30, label %while_entry22, label %next_entry23
while_entry22:
  %v31 = load i32, i32* %v17
  %v32 = getelementptr i32, i32* %v16, i32 0, i32 %v31
  %v33 = load i32, i32* %v15
  %v35 = srem i32 %v33, 10
  store i32 %v35, i32* %v32
  %v36 = load i32, i32* %v15
  %v38 = sdiv i32 %v36, 10
  store i32 %v38, i32* %v15
  %v39 = load i32, i32* %v17
  %v41 = sub nsw i32 %v39, 1
  store i32 %v41, i32* %v17
  br i1 %bool_30, label %while_entry22, label %next_entry23
next_entry23:
  ret i32 0
}
define i32 @main() {
main43:
  store i32 4, i32* @N9
  store i32 10, i32* @newline11
  %v46 = alloca i32
  store i32 zeroinitializer, i32* %v46
  %v48 = alloca i32
  store i32 zeroinitializer, i32* %v48
  %v52 = alloca [4 x i32]
  %v55 = getelementptr [4 x i32], [4 x i32]* %v52, i32 0, i32 0
  store i32 zeroinitializer, i32* %v55
  %v57 = getelementptr [4 x i32], [4 x i32]* %v52, i32 0, i32 1
  store i32 zeroinitializer, i32* %v57
  %v59 = getelementptr [4 x i32], [4 x i32]* %v52, i32 0, i32 2
  store i32 zeroinitializer, i32* %v59
  %v61 = getelementptr [4 x i32], [4 x i32]* %v52, i32 0, i32 3
  store i32 zeroinitializer, i32* %v61
  store i32 1478, i32* %v48
  %v63 = load i32, i32* %v48
  %v64 = load [4 x i32], [4 x i32]* %v52
  %v65 = call i32 @split(i32 %v63, [4 x i32] %v64)
  store i32 %v65, i32* %v48
  %v66 = alloca i32
  store i32 zeroinitializer, i32* %v66
  store i32 0, i32* %v46
  %v71 = load i32, i32* %v46
  %bool_73 = icmp slt i32 %v71, 4
  %bool_75 = icmp ne i1 %bool_73, false
  br i1 %bool_75, label %while_entry69, label %next_entry70
while_entry69:
  %v76 = load i32, i32* %v46
  %v77 = getelementptr [4 x i32], [4 x i32]* %v52, i32 0, i32 %v76
  %v78 = load i32, i32* %v77
  store i32 %v78, i32* %v66
  %v79 = load i32, i32* %v66
  call void @putint(i32 %v79)
  %v81 = load i32, i32* @newline11
  call void @putch(i32 %v81)
  %v83 = load i32, i32* %v46
  %v85 = add nsw i32 %v83, 1
  store i32 %v85, i32* %v46
  br i1 %bool_75, label %while_entry69, label %next_entry70
next_entry70:
  ret i32 0
}

