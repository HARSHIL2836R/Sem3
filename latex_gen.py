# import os

# course_name = "Computer Architecture"


# def generate_latex(base_dir, output_file=f"{course_name}.tex"):
#     # weeks = [d for d in sorted(os.listdir(base_dir)) if os.path.isdir(
#     # os.path.join(base_dir, d)) and d.startswith("Week")]
#     weeks = ["Week1", "Week2", "Week3", "Week4", "Week5",
#              "Week6", "Week7", "Week8", "Week9", "Week10", "Week11"]

#     with open(output_file, "w") as f:
#         # Write the header of the LaTeX document
#         f.write(r"\documentclass[aspectratio = 169]{beamer}" + "\n")
#         f.write(r"\usetheme{Madrid}" + "\n")
#         f.write(r"\usepackage{pdfpages}" + "\n")
#         f.write(r"\usepackage{hyperref}" + "\n")
#         f.write(r"\title{"+course_name+"}" + "\n")
#         f.write(r"\begin{document}" + "\n\n")
#         f.write(r"\maketitle" + "\n")
#         f.write(r"\begin{frame}{TOC}" + "\n")
#         f.write(r"\tableofcontents[sections=1-3]" + "\n")
#         f.write(r"\end{frame}" + "\n")
#         f.write(r"\begin{frame}{TOC}" + "\n")
#         f.write(r"\tableofcontents[sections=4-7]" + "\n")
#         f.write(r"\end{frame}" + "\n")
#         f.write(r"\begin{frame}{TOC}" + "\n")
#         f.write(r"\tableofcontents[sections=8-11]" + "\n")
#         f.write(r"\end{frame}" + "\n")

#         # Process each week directory
#         for week in weeks:
#             week_path = os.path.join(base_dir, week)
#             pdf_files = [f for f in sorted(
#                 os.listdir(week_path)) if f.endswith(".pdf")]

#             # Add the week as a section
#             f.write(rf"\section{{{week}}}" + "\n")
#             f.write(r"\begin{frame}" + f"{{{week}}}" + "\n")
#             f.write(r"\end{frame}" + "\n")
#             # Process each PDF file in the week folder
#             for idx, pdf_file in enumerate(pdf_files, start=1):
#                 pdf_path = os.path.join(week, pdf_file).replace(
#                     "\\", "/")
#                 print(f"Adding {pdf_path} to the document...")
#                 subsection_title = f"{pdf_file}"

#                 # Add the file as a subsection in the TOC
#                 f.write(rf"\section{{{subsection_title.replace("_"," ")}}}" + "\n")
#                 f.write(r"\begin{frame}" + f"{{{pdf_file.replace("_"," ")}}}" + "\n")
#                 f.write(r"\end{frame}" + "\n")
#                 f.write(
#                     r"\includepdf[pages=-]")
#                 f.write("{"+pdf_path+"}" + "\n")

#             # Add a new page after each week
#             f.write(r"\newpage" + "\n\n")

#         # End the document
#         f.write(r"\end{document}" + "\n")

#     print(f"LaTeX file '{output_file}' generated successfully.")


# # Run the function with the current directory
# generate_latex("..")
import os

course_name = "Computer Architecture"


def generate_latex(base_dir, output_file=f"{course_name}_merged.tex"):
    # weeks = [d for d in sorted(os.listdir(base_dir)) if os.path.isdir(
    # os.path.join(base_dir, d)) and d.startswith("Week")]

    with open(output_file, "w") as f:
        # Write the header of the LaTeX document
        f.write(r"\documentclass[aspectratio = 169]{beamer}" + "\n")
        f.write(r"\usetheme{Madrid}" + "\n")
        f.write(r"\usepackage{pdfpages}" + "\n")
        f.write(r"\usepackage{hyperref}" + "\n")
        f.write(r"\title{"+course_name+"}" + "\n")
        f.write(r"\begin{document}" + "\n\n")
        f.write(r"\maketitle" + "\n")
        pdf_files = []
        weeks = ["Week1", "Week2", "Week3", "Week4", "Week5",
                 "Week6", "Week7", "Week8", "Week9", "Week10", "Week11"]
        for week in weeks:
            pdf_files += [week+"/" + f for f in sorted(os.listdir(
                os.path.join(base_dir, week))) if f.endswith(".pdf")]
        for i in range(1, pdf_files.__len__()+1, 8):
            f.write(r"\begin{frame}{TOC}" + "\n")
            f.write(r"\tableofcontents[sections="+str(i) +
                    "-"+str(min(i+7, len(pdf_files))) + "]\n")
            f.write(r"\end{frame}" + "\n")

        # Add the week as a section
        # Process each PDF file in the week folder
        for idx, pdf_file in enumerate(pdf_files, start=1):
            pdf_path = os.path.join(base_dir, pdf_file).replace(
                "\\", "/")
            print(f"Adding {pdf_path} to the document...")
            section_title = f"{pdf_file}"

            # Add the file as a subsection in the TOC
            f.write(rf"\section{{{section_title.replace("_"," ")}}}" + "\n")
            f.write(r"\begin{frame}" + f"{{{pdf_file.replace("_"," ")}}}" + "\n")
            f.write(r"\end{frame}" + "\n")
            f.write(
                r"\includepdf[pages=-]")
            f.write("{"+pdf_path+"}" + "\n")

        # Add a new page after each week
        f.write(r"\newpage" + "\n\n")

        # End the document
        f.write(r"\end{document}" + "\n")

        print(f"LaTeX file '{output_file}' generated successfully.")


# Run the function with the current directory
generate_latex("..")
