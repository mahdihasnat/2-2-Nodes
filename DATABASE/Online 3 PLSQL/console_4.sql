--- ans 1

declare
    total      number;
    new_salary number;
begin
    total := 0;
    for cursor IN (select *
                   from hr.EMPLOYEES e1
                   where (select count(*) from hr.EMPLOYEES e2 where e2.MANAGER_ID = e1.EMPLOYEE_ID) > 0
                     and months_between(sysdate, HIRE_DATE) >= 24 )
        loop
            new_salary := cursor.SALARY * 1.15;
            update hr.EMPLOYEES
            set SALARY = new_salary
            where EMPLOYEE_ID = cursor.EMPLOYEE_ID;
            DBMS_OUTPUT.PUT_LINE(cursor.LAST_NAME || ' ' || cursor.SALARY || ' ' || new_salary);
            total := total + 1;
        end loop;
    DBMS_OUTPUT.PUT_LINE('total change: ' || total);
end;
/


--- ans 2
create or replace procedure hr.INTERCHANGE_SALARY(eid1 in number, eid2 in number) is
    sal1 number;
    sal2 number;
begin
    select SALARY into sal1 from hr.EMPLOYEES where EMPLOYEE_ID = eid1;
    select SALARY into sal2 from hr.EMPLOYEES where EMPLOYEE_ID = eid1;

    update hr.EMPLOYEES
    set SALARY = sal2
    where EMPLOYEE_ID = eid1;

    update hr.EMPLOYEES
    set SALARY = sal1
    where EMPLOYEE_ID = eid2;

    DBMS_OUTPUT.PUT_LINE('old sal 1 : ' || sal1 || ' new sal 1: ' || sal2);
    DBMS_OUTPUT.PUT_LINE('old sal 2 : ' || sal2 || ' new sal 2: ' || sal1);

Exception
    when no_data_found then
        DBMS_OUTPUT.PUT_LINE('wrong id');
end;
/

begin
    hr.INTERCHANGE_SALARY(100, 101);
    hr.INTERCHANGE_SALARY(10, 101);
end;
/

--- ans 3

create or replace function CNT_ACCOUNTING_SENIOR return number is
    cnt number;
begin
    cnt := 0;
    for cursor in
        (
        select EMPLOYEE_ID, LAST_NAME
        from hr.EMPLOYEES e
                 join hr.DEPARTMENTS d on (e.DEPARTMENT_ID = d.DEPARTMENT_ID)
        where d.DEPARTMENT_NAME = 'Accounting'
          and months_between(sysdate, e.HIRE_DATE) > 20 * 12
        )
        loop
            DBMS_OUTPUT.PUT_LINE(cursor.LAST_NAME || ' wu=ith eid ' || cursor.EMPLOYEE_ID ||
                                 '  working for more then 20 years in accounting ');
            cnt := cnt + 1;
        end loop;
    return cnt;
end;
/
begin
    DBMS_OUTPUT.PUT_LINE('total: ' || CNT_ACCOUNTING_SENIOR());
end;
/

--- ans 4
create table hr.Employee_2
(
    EMPLOYEE_ID    NUMBER(6)    NOT NULL,
    FIRST_NAME     VARCHAR2(20),
    LAST_NAME      VARCHAR2(25) NOT NULL,
    EMAIL          VARCHAR2(25) NOT NULL,
    PHONE_NUMBER   VARCHAR2(20),
    HIRE_DATE      DATE         NOT NULL,
    JOB_ID         VARCHAR2(10) NOT NULL,
    SALARY         NUMBER(8, 2),
    COMMISSION_PCT NUMBER(2, 2),
    MANAGER_ID     NUMBER(6),
    DEPARTMENT_ID  NUMBER(4)
);

insert into hr.Employee_2 (select * from hr.EMPLOYEES);

create or replace trigger hr.NO_DEC
    before update
    on hr.Employee_2
    for each row
begin
    if :new.salary < :old.salary then
        raise_application_error(-20111, 'salary cannot less than previous salary');
    end if;
end;
/