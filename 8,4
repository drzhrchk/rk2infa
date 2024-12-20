CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    quantity INTEGER NOT NULL CHECK (quantity >= 0)
);

CREATE TABLE operations_log (
    id SERIAL PRIMARY KEY,
    product_id INTEGER REFERENCES products(id),
    operation VARCHAR(10) NOT NULL CHECK (operation IN ('ADD', 'REMOVE')),
    quantity INTEGER NOT NULL,
    operation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE OR REPLACE PROCEDURE update_stock(
    p_product_id INT,
    p_operation VARCHAR(10),
    p_quantity INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    current_quantity INTEGER;
BEGIN
    IF p_operation NOT IN ('ADD', 'REMOVE') THEN
        RAISE EXCEPTION 'Недопустимый тип операции: %', p_operation;
    END IF;

    SELECT quantity INTO current_quantity FROM products WHERE id = p_product_id;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Товар с ID % не найден.', p_product_id;
    END IF;

    IF p_operation = 'ADD' THEN
        UPDATE products SET quantity = current_quantity + p_quantity WHERE id = p_product_id;
    ELSIF p_operation = 'REMOVE' THEN
        IF current_quantity - p_quantity < 0 THEN
            RAISE EXCEPTION 'Недостаточно товара на складе для удаления.';
        ELSE
            UPDATE products SET quantity = current_quantity - p_quantity WHERE id = p_product_id;
        END IF;
    END IF;

    INSERT INTO operations_log (product_id, operation, quantity)
    VALUES (p_product_id, p_operation, p_quantity);
    
    COMMIT;

EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        RAISE;
END;
$$;

CREATE OR REPLACE FUNCTION log_product_changes()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'UPDATE') THEN
        IF NEW.quantity <> OLD.quantity THEN
           INSERT INTO operations_log (product_id, operation, quantity)
           VALUES (
             OLD.id,
              CASE WHEN NEW.quantity > OLD.quantity THEN 'ADD' ELSE 'REMOVE' END,
              ABS(NEW.quantity - OLD.quantity)
           );
         END IF;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER product_changes_trigger
AFTER UPDATE ON products
FOR EACH ROW
EXECUTE FUNCTION log_product_changes();
