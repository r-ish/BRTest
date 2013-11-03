del /S tags
ctags --langmap=c:.c.iram --excmd=number --tag-relative=yes --recurse=yes -f - | htags > tags
