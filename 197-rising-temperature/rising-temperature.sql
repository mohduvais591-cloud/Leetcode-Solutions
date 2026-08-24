SELECT id
FROM Weather
WHERE temperature > (
    SELECT temperature
    FROM Weather w2
    WHERE DATEDIFF(Weather.recordDate, w2.recordDate) = 1
);