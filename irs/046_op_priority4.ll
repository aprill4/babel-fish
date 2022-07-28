@a9 = global i32 zeroinitializer
@b11 = global i32 zeroinitializer
@c13 = global i32 zeroinitializer
@d15 = global i32 zeroinitializer
@e17 = global i32 zeroinitializer
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
main18:
  %v19 = call i32 @getint()
  store i32 %v19, i32* @a9
  %v20 = call i32 @getint()
  store i32 %v20, i32* @b11
  %v21 = call i32 @getint()
  store i32 %v21, i32* @c13
  %v22 = call i32 @getint()
  store i32 %v22, i32* @d15
  %v23 = call i32 @getint()
  store i32 %v23, i32* @e17
  %v24 = alloca i32
  store i32 0, i32* %v24
  %v33 = load i32, i32* @a9
  %v34 = load i32, i32* @b11
  %v35 = load i32, i32* @c13
  %v36 = mul i32 %v34, %v35
  %v37 = sub nsw i32 %v33, %v36
  %v38 = load i32, i32* @d15
  %v39 = load i32, i32* @a9
  %v40 = load i32, i32* @c13
  %v41 = sdiv i32 %v39, %v40
  %v42 = sub nsw i32 %v38, %v41
  %bool_43 = icmp ne i32 %v37, %v42
  %bool_45 = icmp ne i1 %bool_43, zeroinitializer
  br i1 %bool_45, label %l31, label %r32
if_true_entry26:
  store i32 1, i32* %v24
  br label %next_entry28
next_entry28:
  %v69 = load i32, i32* %v24
  ret i32 %v69
l29:
  br label %if_true_entry26
r30:
  %v57 = load i32, i32* @a9
  %v58 = load i32, i32* @b11
  %v59 = add nsw i32 %v57, %v58
  %v60 = load i32, i32* @c13
  %v61 = add nsw i32 %v59, %v60
  %v62 = load i32, i32* @d15
  %v63 = load i32, i32* @e17
  %v64 = add nsw i32 %v62, %v63
  %bool_65 = icmp eq i32 %v61, %v64
  %bool_67 = icmp ne i1 %bool_65, zeroinitializer
  br i1 %bool_67, label %l29, label %next_entry28
l31:
  br label %if_true_entry26
r32:
  %v46 = load i32, i32* @a9
  %v47 = load i32, i32* @b11
  %v48 = mul i32 %v46, %v47
  %v49 = load i32, i32* @c13
  %v50 = sdiv i32 %v48, %v49
  %v51 = load i32, i32* @e17
  %v52 = load i32, i32* @d15
  %v53 = add nsw i32 %v51, %v52
  %bool_54 = icmp eq i32 %v50, %v53
  %bool_56 = icmp ne i1 %bool_54, zeroinitializer
  br i1 %bool_56, label %l31, label %r30
}

