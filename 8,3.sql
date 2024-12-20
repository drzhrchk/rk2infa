CREATE TABLE employees (
    employee_id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    department VARCHAR(50) NOT NULL,
    salary INT NOT NULL,
    hire_date DATE NOT NULL
);


INSERT INTO employees (employee_id, name, department, salary, hire_date) VALUES
(1, 'Alice', 'HR', 70000, '2019-01-15'),
(2, 'Bob', 'IT', 90000, '2020-06-01'),
(3, 'Charlie', 'IT', 80000, '2021-03-10'),
(4, 'Diana', 'Marketing', 60000, '2022-11-25');

SELECT 
    employee_id, 
    name, 
    department, 
    salary, 
    hire_date
FROM 
    employees
WHERE 
    department = 'IT' 
    AND hire_date > '2020-12-31'
ORDER BY 
    salary DESC;