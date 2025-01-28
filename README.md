### Video link: https://youtu.be/M_xgjJnVCO4
> ![Image](https://github.com/user-attachments/assets/a59e633d-d16d-40d1-be81-2cea2dab152a)

---

### For Getting all table columns & rows (add this in line 101)
> ```bash
> String endpoint = String(supabaseUrl) + "/rest/v1/" + tableName + "?select=*";
> ```

### For Inserting a new row

#### replace line 53 by this
> ```bash
> String endpoint = String(supabaseUrl) + "/rest/v1/" + tableName;
> ```
> 
#### replace line 62 by this
> ```bash
> int httpResponseCode = http.POST(jsonString);
> ```
