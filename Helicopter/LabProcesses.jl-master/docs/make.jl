using Documenter, LabProcesses
# makedocs()
# deploydocs(
# deps   = Deps.pip("pygments", "mkdocs", "python-markdown-math", "mkdocs-cinder"),
# repo   = "gitlab.control.lth.se/processes/LabProcesses.jl",
# branch = "gh-pages",
# julia  = "0.6",
# osname = "linux"
# )

makedocs(
    format = :html,
    sitename = "LabProcesses",
    pages = [
        "index.md",
    ]
)
