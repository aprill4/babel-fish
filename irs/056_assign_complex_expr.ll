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
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 5, i32* %v9
  store i32 5, i32* %v11
  store i32 1, i32* %v13
  %v24 = sub nsw i32 0, 2
  store i32 %v24, i32* %v15
  %v25 = load i32, i32* %v15
  %v27 = mul i32 %v25, 1
  %v29 = sdiv i32 %v27, 2
  %v30 = load i32, i32* %v9
  %v31 = load i32, i32* %v11
  %v32 = sub nsw i32 %v30, %v31
  %v33 = add nsw i32 %v29, %v32
  %v34 = load i32, i32* %v13
  %v36 = add nsw i32 %v34, 3
  %v38 = sub nsw i32 0, %v36
  %v40 = srem i32 %v38, 2
  %v41 = sub nsw i32 %v33, %v40
  store i32 %v41, i32* %v17
  %v42 = load i32, i32* %v17
  call void @putint(i32 %v42)
  %v44 = load i32, i32* %v15
  %v46 = srem i32 %v44, 2
  %v48 = add nsw i32 %v46, 67
  %v49 = load i32, i32* %v9
  %v50 = load i32, i32* %v11
  %v51 = sub nsw i32 %v49, %v50
  %v53 = sub nsw i32 0, %v51
  %v54 = add nsw i32 %v48, %v53
  %v55 = load i32, i32* %v13
  %v57 = add nsw i32 %v55, 2
  %v59 = srem i32 %v57, 2
  %v61 = sub nsw i32 0, %v59
  %v62 = sub nsw i32 %v54, %v61
  store i32 %v62, i32* %v17
  %v63 = load i32, i32* %v17
  %v65 = add nsw i32 %v63, 3
  store i32 %v65, i32* %v17
  %v66 = load i32, i32* %v17
  call void @putint(i32 %v66)
  ret i32 0
}

