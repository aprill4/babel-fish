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
define i32 @fun(i32 , i32 ) {
fun10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v17 = load i32, i32* %v12
  %bool_19 = icmp sgt i32 %v17, 0
  %bool_21 = icmp ne i1 %bool_19, false
  br i1 %bool_21, label %while_entry15, label %next_entry16
while_entry15:
  %v22 = load i32, i32* %v11
  %v23 = load i32, i32* %v12
  %v24 = srem i32 %v22, %v23
  store i32 %v24, i32* %v13
  %v25 = load i32, i32* %v12
  store i32 %v25, i32* %v11
  %v26 = load i32, i32* %v13
  store i32 %v26, i32* %v12
  br i1 %bool_21, label %while_entry15, label %next_entry16
next_entry16:
  %v27 = load i32, i32* %v11
  ret i32 %v27
}
define i32 @main() {
main28:
  %v29 = alloca i32
  store i32 zeroinitializer, i32* %v29
  %v31 = alloca i32
  store i32 zeroinitializer, i32* %v31
  %v33 = alloca i32
  store i32 zeroinitializer, i32* %v33
  %v35 = call i32 @getint()
  store i32 %v35, i32* %v31
  %v36 = call i32 @getint()
  store i32 %v36, i32* %v29
  %v37 = load i32, i32* %v31
  %v38 = load i32, i32* %v29
  %v39 = call i32 @fun(i32 %v37, i32 %v38)
  store i32 %v39, i32* %v33
  %v40 = load i32, i32* %v33
  call void @putint(i32 %v40)
  ret i32 0
}

