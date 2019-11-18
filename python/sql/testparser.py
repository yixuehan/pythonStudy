#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlparse


def sql_format(sql):
    stmts = sqlparse.split(sql)
    print(stmts)
    for stmt in stmts:
        print(sqlparse.format(stmt, reindent=True, keyword_case="upper"))
        stmt_parsed = sqlparse.parse(stmt)
        print(stmt_parsed[0].tokens)
    print("*" * 80)


if __name__ == '__main__':
    sql = '''
        SELECT a.x, b.y
        FROM t_project_job a inner join t_project_project b
        on a.project_id = b.project_id
        '''
    sql_format(sql)
    sql = '''
        SELECT * FROM wangkai_dev.t_online_service_apply where service_id = srv5klnzc38ngr04'
    '''
    sql_format(sql)
    sql = '''
        select online.*, ifnull(apply.apply_id, '') as apply_id, ifnull(apply.audit_status, 'Unaudited') as audit_status,
               apply.update_time as audit_time, task.model_code_text as code_text, task.model_name, task.task_id, task.status as task_status
         from (t_online_service as online left join t_online_service_apply as apply on online.service_id = apply.service_id)
              inner join t_task as task on task.task_id = online.task_id
         where online.user_id = 'uid'
          and ('pid' = '' or online.project_id = 'pid')
          and ('sid' = '' or 'sid' = online.service_id)
          and task.task_type = 'debug'
          and online.online_service_status != 'enable'
         order by apply.update_time desc
         limit 1
    '''
    sql_format(sql)
