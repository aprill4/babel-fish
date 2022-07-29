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
define i32 @deepWhileBr(i32 , i32 ) {
deepWhileBr10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = load i32, i32* %v11
  %v16 = load i32, i32* %v12
  %v17 = add nsw i32 %v15, %v16
  store i32 %v17, i32* %v13
  %v20 = load i32, i32* %v13
  %bool_22 = icmp slt i32 %v20, 75
  %bool_24 = icmp ne i1 %bool_22, false
  br i1 %bool_24, label %while_entry18, label %next_entry19
while_entry18:
  %v25 = alloca i32
  store i32 zeroinitializer, i32* %v25
  store i32 42, i32* %v25
  %v31 = load i32, i32* %v13
  %bool_33 = icmp slt i32 %v31, 100
  br i1 %bool_33, label %if_true_entry28, label %next_entry30
next_entry19:
  %v57 = load i32, i32* %v13
  ret i32 %v57
if_true_entry28:
  %v34 = load i32, i32* %v13
  %v35 = load i32, i32* %v25
  %v36 = add nsw i32 %v34, %v35
  store i32 %v36, i32* %v13
  %v40 = load i32, i32* %v13
  %bool_42 = icmp sgt i32 %v40, 99
  br i1 %bool_42, label %if_true_entry37, label %next_entry39
next_entry30:
  br i1 %bool_24, label %while_entry18, label %next_entry19
if_true_entry37:
  %v43 = alloca i32
  store i32 zeroinitializer, i32* %v43
  %v45 = load i32, i32* %v25
  %v47 = mul i32 %v45, 2
  store i32 %v47, i32* %v43
  %bool_53 = icmp eq i32 1, 1
  br i1 %bool_53, label %if_true_entry48, label %next_entry50
next_entry39:
  br label %next_entry30
if_true_entry48:
  %v54 = load i32, i32* %v43
  %v56 = mul i32 %v54, 2
  store i32 %v56, i32* %v13
  br label %next_entry50
next_entry50:
  br label %next_entry39
}
define i32 @main() {
main58:
  %v59 = alloca i32
  store i32 zeroinitializer, i32* %v59
  store i32 2, i32* %v59
  %v62 = load i32, i32* %v59
  %v63 = load i32, i32* %v59
  %v64 = call i32 @deepWhileBr(i32 %v62, i32 %v63)
  ret i32 %v64
}

