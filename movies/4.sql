SELECT
  COUNT(*) AS num_rows
FROM
  (
    SELECT
      movie_id
    FROM
      ratings
    WHERE
      rating = 10.0
  );