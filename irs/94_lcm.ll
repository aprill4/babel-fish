@n9 = global i32 zeroinitializer
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
define i32 @gcd(i32 , i32 ) {
gcd12:
  %v13 = alloca i32
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  %v19 = load i32, i32* %v13
  store i32 %v19, i32* %v15
  %v20 = load i32, i32* %v14
  store i32 %v20, i32* %v17
  %v21 = alloca i32
  store i32 zeroinitializer, i32* %v21
  %v23 = alloca i32
  store i32 zeroinitializer, i32* %v23
  %v28 = load i32, i32* %v13
  %v29 = load i32, i32* %v14
  %bool_30 = icmp slt i32 %v28, %v29
  br i1 %bool_30, label %if_true_entry25, label %next_entry27
if_true_entry25:
  %v31 = load i32, i32* %v13
  store i32 %v31, i32* %v21
  %v32 = load i32, i32* %v14
  store i32 %v32, i32* %v13
  %v33 = load i32, i32* %v21
  store i32 %v33, i32* %v14
  br label %next_entry27
next_entry27:
  %v34 = load i32, i32* %v13
  %v35 = load i32, i32* %v14
  %v36 = srem i32 %v34, %v35
  store i32 %v36, i32* %v23
  %v39 = load i32, i32* %v23
  %bool_41 = icmp ne i32 %v39, 0
  %bool_43 = icmp ne i1 %bool_41, false
  br i1 %bool_43, label %while_entry37, label %next_entry38
while_entry37:
  %v44 = load i32, i32* %v14
  store i32 %v44, i32* %v13
  %v45 = load i32, i32* %v23
  store i32 %v45, i32* %v14
  %v46 = load i32, i32* %v13
  %v47 = load i32, i32* %v14
  %v48 = srem i32 %v46, %v47
  store i32 %v48, i32* %v23
  br i1 %bool_43, label %while_entry37, label %next_entry38
next_entry38:
  %v49 = load i32, i32* %v15
  %v50 = load i32, i32* %v17
  %v51 = mul i32 %v49, %v50
  %v52 = load i32, i32* %v14
  %v53 = sdiv i32 %v51, %v52
  ret i32 %v53
}
define i32 @main() {
main54:
  %v55 = alloca i32
  store i32 zeroinitializer, i32* %v55
  %v57 = alloca i32
  store i32 zeroinitializer, i32* %v57
  %v59 = call i32 @getint()
  store i32 %v59, i32* %v55
  %v60 = call i32 @getint()
  store i32 %v60, i32* %v57
  %v61 = load i32, i32* %v55
  %v62 = load i32, i32* %v57
  %v63 = call i32 @gcd(i32 %v61, i32 %v62)
  ret i32 %v63
}

