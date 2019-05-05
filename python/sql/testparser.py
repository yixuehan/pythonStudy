#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlparse

if __name__ == '__main__':
    sql = '''
            SELECT a.x, b.y
            FROM t_project_job a inner join t_project_project b
            on a.project_id = b.project_id
        '''
    ress = sqlparse.parse(sql)
    print(len(ress))
    # sqlparse.tokens.Whitespace
    for token in ress[0].tokens:
        if token.ttype != sqlparse.tokens.Whitespace and \
           token.ttype != sqlparse.tokens.Newline:
            print(type(token.ttype), token.ttype, token.value)
