while (current != NULL && i < 5) // Display up to 10 patients
    {
      mvwprintw(win, display_y + (i * 2), 4, "%d. %s %s (Patient ID: %d)",
                i + 1, current->first_name, current->last_name, current->id);
      current = current->next_patient;
      i++;
    }
    if (current != NULL)
    {
      while (true)
      {
        mvwprintw(
            win, display_y + (i * 2), 4,
            "Press N to see the or Q to Quit"); // Indicate more patients

        char c = wgetch(win);
        if (tolower(c) == 'q')
        {
          return;
        }
        else if (tolower(c) == 'n')
        {
          break;
        }
        else
        {
          mvwprintw(win, display_y + (i * 2), 4,
                    "Invalid option select try again");
          // nodelay();
          continue;
        }
      }
      // Next line
    }
    else
    {
      mvwprintw(win, 16, (width - 25) / 2, "Press any key to return...");
      wrefresh(win);
      wgetch(win); // Wait for user to read success message
      return;
    }
  }
}

  else
  {

    Patient_Node *current = queue->head;
    int i = 0;
    int display_y = 5; // Starting Y position for displaying patients
    whil
