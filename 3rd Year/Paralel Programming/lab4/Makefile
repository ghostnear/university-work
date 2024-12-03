.PHONY: all

c:
	@rm -rf bin
	@rm -rf obj

ed:
	@dotnet run http://httpforever.com /index.html event-driven

aa:
	@dotnet run http://httpforever.com /index.html async-await

tb:
	@dotnet run http://httpforever.com /index.html task-based

f_ed:
	@dotnet run http://httpforever.com /index.html event-driven > bin/output_ed.txt

f_aa:
	@dotnet run http://httpforever.com /index.html async-await > bin/output_aa.txt

f_tb:
	@dotnet run http://httpforever.com /index.html task-based > bin/output_tb.txt

compare: f_ed f_aa f_tb
	@if cmp -s bin/output_ed.txt bin/output_aa.txt && cmp -s bin/output_aa.txt bin/output_tb.txt; then \
        echo "All outputs are identical."; \
    else \
        echo "There are differences in the outputs."; \
    fi
