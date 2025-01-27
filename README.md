### Video link: https://youtu.be/M_xgjJnVCO4
> ![ESP32 - Azure IoT](https://github.com/user-attachments/assets/4d8a4eba-eec1-4c11-a996-879d8f77e96b)

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
